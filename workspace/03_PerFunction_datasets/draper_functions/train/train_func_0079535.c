run_run()
{
      vvp_net_t*ptr = net_;
      net_ = 0;

      vvp_vector4_t tmp (input_);
      tmp.change_z2x();
      vvp_send_vec4(ptr->out, tmp, 0);
}
