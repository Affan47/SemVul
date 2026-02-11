validate_geometry_shader_executable(struct gl_shader_program *prog,
				    struct gl_shader *shader)
{
   if (shader == NULL)
      return;

   unsigned num_vertices = vertices_per_prim(prog->Geom.InputType);
   prog->Geom.VerticesIn = num_vertices;

   analyze_clip_usage(prog, shader, &prog->Geom.UsesClipDistance,
                      &prog->Geom.ClipDistanceArraySize);

   find_end_primitive_visitor end_primitive;
   end_primitive.run(shader->ir);
   prog->Geom.UsesEndPrimitive = end_primitive.end_primitive_found();
}
