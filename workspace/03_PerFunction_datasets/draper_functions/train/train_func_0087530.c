pform_start_generate_nblock(const struct vlltype&li, char*name)
{
      PGenerate*gen = new PGenerate(scope_generate_counter++);

      FILE_NAME(gen, li);

      gen->parent = pform_cur_generate;
      pform_cur_generate = gen;

      pform_cur_generate->scheme_type = PGenerate::GS_NBLOCK;

      pform_cur_generate->loop_init = 0;
      pform_cur_generate->loop_test = 0;
      pform_cur_generate->loop_step = 0;

      pform_cur_generate->scope_name = lex_strings.make(name);
      delete[]name;
}
