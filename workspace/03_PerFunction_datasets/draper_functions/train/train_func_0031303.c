lower_ubo_reference(struct gl_shader *shader, exec_list *instructions)
{
   lower_ubo_reference_visitor v(shader);


   do {
      v.progress = false;
      visit_list_elements(&v, instructions);
   } while (v.progress);
}
