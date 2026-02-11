lp_build_emit_llvm(
   struct lp_build_tgsi_context *bld_base,
   unsigned tgsi_opcode,
   struct lp_build_emit_data * emit_data)
{
   struct lp_build_tgsi_action * action = &bld_base->op_actions[tgsi_opcode];


   lp_build_action_set_dst_type(emit_data, bld_base, tgsi_opcode);
   emit_data->chan = 0;
   assert(action->emit);
   action->emit(action, bld_base, emit_data);
   return emit_data->output[0];
}
