gradientcomputer_(double *g, double *x, void* userdata)
{
  vnl_conjugate_gradient* self =
    static_cast<vnl_conjugate_gradient*>(userdata);
  vnl_cost_function* f = self->f_;
  vnl_vector_ref<double> ref_x(f->get_number_of_unknowns(), x);
  vnl_vector_ref<double> ref_g(f->get_number_of_unknowns(), g);

  f->gradf(ref_x, ref_g);
}
