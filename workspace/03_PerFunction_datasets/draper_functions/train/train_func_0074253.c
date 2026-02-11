st_translate_vertex_program(struct st_context *st,
                            struct st_vertex_program *stvp,
                            const struct st_vp_variant_key *key)
{
   struct st_vp_variant *vpv = CALLOC_STRUCT(st_vp_variant);
   struct pipe_context *pipe = st->pipe;
   struct ureg_program *ureg;
   enum pipe_error error;
   unsigned num_outputs;

   st_prepare_vertex_program(st->ctx, stvp);

   if (!stvp->glsl_to_tgsi)
   {
      _mesa_remove_output_reads(&stvp->Base.Base, PROGRAM_OUTPUT);
   }

   ureg = ureg_create( TGSI_PROCESSOR_VERTEX );
   if (ureg == NULL) {
      free(vpv);
      return NULL;
   }

   vpv->key = *key;

   vpv->num_inputs = stvp->num_inputs;
   num_outputs = stvp->num_outputs;
   if (key->passthrough_edgeflags) {
      vpv->num_inputs++;
      num_outputs++;
   }

   if (ST_DEBUG & DEBUG_MESA) {
      _mesa_print_program(&stvp->Base.Base);
      _mesa_print_program_parameters(st->ctx, &stvp->Base.Base);
      debug_printf("\n");
   }

   if (stvp->glsl_to_tgsi)
      error = st_translate_program(st->ctx,
                                   TGSI_PROCESSOR_VERTEX,
                                   ureg,
                                   stvp->glsl_to_tgsi,
                                   &stvp->Base.Base,

                                   stvp->num_inputs,
                                   stvp->input_to_index,
                                   NULL,
                                   NULL,
                                   NULL,
                                   NULL,

                                   stvp->num_outputs,
                                   stvp->result_to_output,
                                   stvp->output_semantic_name,
                                   stvp->output_semantic_index,
                                   key->passthrough_edgeflags,
                                   key->clamp_color);
   else
      error = st_translate_mesa_program(st->ctx,
                                        TGSI_PROCESSOR_VERTEX,
                                        ureg,
                                        &stvp->Base.Base,

                                        vpv->num_inputs,
                                        stvp->input_to_index,
                                        NULL,
                                        NULL,
                                        NULL,

                                        num_outputs,
                                        stvp->result_to_output,
                                        stvp->output_semantic_name,
                                        stvp->output_semantic_index,
                                        key->passthrough_edgeflags,
                                        key->clamp_color);

   if (error)
      goto fail;

   vpv->tgsi.tokens = ureg_get_tokens( ureg, NULL );
   if (!vpv->tgsi.tokens)
      goto fail;

   ureg_destroy( ureg );

   if (stvp->glsl_to_tgsi) {
      st_translate_stream_output_info(stvp->glsl_to_tgsi,
                                      stvp->result_to_output,
                                      &vpv->tgsi.stream_output);
   }

   vpv->driver_shader = pipe->create_vs_state(pipe, &vpv->tgsi);

   if (ST_DEBUG & DEBUG_TGSI) {
      tgsi_dump( vpv->tgsi.tokens, 0 );
      debug_printf("\n");
   }

   return vpv;

fail:
   debug_printf("%s: failed to translate Mesa program:\n", __FUNCTION__);
   _mesa_print_program(&stvp->Base.Base);
   debug_assert(0);

   ureg_destroy( ureg );
   return NULL;
}
