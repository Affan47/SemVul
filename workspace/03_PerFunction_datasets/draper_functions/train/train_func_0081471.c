cl_process (GeglOperation       *op,
            cl_mem               in_tex,
            cl_mem               aux_tex,
            cl_mem               out_tex,
            size_t               global_worksize,
            const GeglRectangle *roi,
            gint                 level)
{
  gfloat value = GEGL_CHANT_PROPERTIES (op)->value;

  cl_int cl_err = 0;

  if (!cl_data)
    {
      const char *kernel_name[] = {"kernel_thr_3", "kernel_thr_2", NULL};
      cl_data = gegl_cl_compile_and_build (kernel_source, kernel_name);
    }

  if (!cl_data) return 1;

  if (aux_tex)
    {
      cl_err |= gegl_clSetKernelArg(cl_data->kernel[0], 0, sizeof(cl_mem),   (void*)&in_tex);
      cl_err |= gegl_clSetKernelArg(cl_data->kernel[0], 1, sizeof(cl_mem),   (void*)&aux_tex);
      cl_err |= gegl_clSetKernelArg(cl_data->kernel[0], 2, sizeof(cl_mem),   (void*)&out_tex);
      if (cl_err != CL_SUCCESS) return cl_err;

      cl_err = gegl_clEnqueueNDRangeKernel(gegl_cl_get_command_queue (),
                                            cl_data->kernel[0], 1,
                                            NULL, &global_worksize, NULL,
                                            0, NULL, NULL);
      if (cl_err != CL_SUCCESS) return cl_err;
    }
  else
    {
      cl_err |= gegl_clSetKernelArg(cl_data->kernel[1], 0, sizeof(cl_mem),   (void*)&in_tex);
      cl_err |= gegl_clSetKernelArg(cl_data->kernel[1], 1, sizeof(cl_mem),   (void*)&out_tex);
      cl_err |= gegl_clSetKernelArg(cl_data->kernel[1], 2, sizeof(cl_float), (void*)&value);
      if (cl_err != CL_SUCCESS) return cl_err;

      cl_err = gegl_clEnqueueNDRangeKernel(gegl_cl_get_command_queue (),
                                            cl_data->kernel[1], 1,
                                            NULL, &global_worksize, NULL,
                                            0, NULL, NULL);
      if (cl_err != CL_SUCCESS) return cl_err;
    }

  return cl_err;
}
