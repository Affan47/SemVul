preconditioner_( double *out, double *in, void* userdata)
{


  vnl_conjugate_gradient* self =
    static_cast<vnl_conjugate_gradient*>(userdata);
  vnl_cost_function* f = self->f_;

  int n = f->get_number_of_unknowns();
  for (int i=0; i < n; ++i)
    out[i] = in[i];
}
