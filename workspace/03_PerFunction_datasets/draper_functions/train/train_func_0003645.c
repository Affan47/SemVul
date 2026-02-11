P_Vector_Ref (Object vec, Object n) {
    Check_Type (vec, T_Vector);
    return VECTOR(vec)->data[Get_Index (n, vec)];
}
