v_homo2(vector, v_result)
const hvec2_t *vector;
hvec2_t *v_result;
{
   v_result = gm_ALLOC(hvec2_t, v_result, "v_homo2()");

   v_x(*v_result) = gm_DIV(v_x(*vector), v_w(*vector), "v_homo2()");
   v_y(*v_result) = v_y(*vector) / v_w(*vector);
   v_w(*v_result) = 1.0;

   return v_result;
}
