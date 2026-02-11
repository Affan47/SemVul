sv_mul3(scalar, vector, v_result)
double  scalar;
const hvec3_t *vector;
hvec3_t *v_result;
{
   v_result = gm_ALLOC(hvec3_t, v_result, "sv_mul3()");

   v_x(*v_result) = v_x(*vector) * scalar;
   v_y(*v_result) = v_y(*vector) * scalar;
   v_z(*v_result) = v_z(*vector) * scalar;
   v_w(*v_result) = v_w(*vector);

   return  v_result;
}
