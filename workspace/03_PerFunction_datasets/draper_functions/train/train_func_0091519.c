cl_bilateral_filter (cl_mem                in_tex,
                     cl_mem                out_tex,
                     size_t                global_worksize,
                     const GeglRectangle  *roi,
                     gfloat                radius,
                     gfloat                preserve)
{
  cl_int cl_err = 0;
  size_t global_ws[2];

  if (!cl_data)
  {
    const char *kernel_name[] = {"bilateral_filter", NULL};
    cl_data = gegl_cl_compile_and_build (kernel_source, kernel_name);
  }

  if (!cl_data) return 1;

  global_ws[0] = roi->width;
  global_ws[1] = roi->height;

  cl_err |= gegl_clSetKernelArg(cl_data->kernel[0], 0, sizeof(cl_mem),   (void*)&in_tex);
  cl_err |= gegl_clSetKernelArg(cl_data->kernel[0], 1, sizeof(cl_mem),   (void*)&out_tex);
  cl_err |= gegl_clSetKernelArg(cl_data->kernel[0], 2, sizeof(cl_float), (void*)&radius);
  cl_err |= gegl_clSetKernelArg(cl_data->kernel[0], 3, sizeof(cl_float), (void*)&preserve);
  if (cl_err != CL_SUCCESS) return cl_err;

  cl_err = gegl_clEnqueueNDRangeKernel(gegl_cl_get_command_queue (),
                                       cl_data->kernel[0], 2,
                                       NULL, global_ws, NULL,
                                       0, NULL, NULL);
  if (cl_err != CL_SUCCESS) return cl_err;

  return cl_err;
}
