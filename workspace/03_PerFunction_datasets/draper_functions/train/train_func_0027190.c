gstspu_blend_comp_buffers (SpuState * state, guint8 * planes[3])
{
  gint16 uv_end;
  gint16 left, x;
  guint8 *out_U;
  guint8 *out_V;
  guint32 *in_U;
  guint32 *in_V;
  guint32 *in_A;
  gint16 comp_last_x = state->comp_right;

  if (comp_last_x < state->comp_left)
    return;

#if 0
  GST_LOG ("Blending comp buffers from x=%d to x=%d",
      state->comp_left, state->comp_right);
#endif


  out_U = planes[1];
  out_V = planes[2];


  in_U = state->comp_bufs[0];
  in_V = state->comp_bufs[1];
  in_A = state->comp_bufs[2];


  uv_end = (comp_last_x + 1) / 2;
  left = state->comp_left / 2;

  for (x = left; x < uv_end; x++) {
    guint32 tmp;


    guint16 inv_A = (4 * 0xff) - in_A[x];

    tmp = in_U[x] + inv_A * out_U[x];
    out_U[x] = (guint8) (tmp / (4 * 0xff));

    tmp = in_V[x] + inv_A * out_V[x];
    out_V[x] = (guint8) (tmp / (4 * 0xff));
  }
}
