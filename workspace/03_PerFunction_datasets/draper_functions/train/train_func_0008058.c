set_block_binding(gl_shader_program *prog, const char *block_name, int binding)
{
   const unsigned block_index = get_uniform_block_index(prog, block_name);

   if (block_index == GL_INVALID_INDEX) {
      assert(block_index != GL_INVALID_INDEX);
      return;
   }


      for (int i = 0; i < MESA_SHADER_STAGES; i++) {
         int stage_index = prog->UniformBlockStageIndex[i][block_index];

         if (stage_index != -1) {
            struct gl_shader *sh = prog->_LinkedShaders[i];
            sh->UniformBlocks[stage_index].Binding = binding;
         }
      }
}
