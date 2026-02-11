count_temp_in_operand(Operand *arg)
{
    Operand   *sub;
    int       total = 0;

    if (arg->kind == KIND_ARRAY
     || arg->kind == KIND_SUB
     || arg->kind == KIND_FUNC
     || arg->kind == KIND_INTFUNC) {
      for (sub=arg->inner ; sub!=NULL ; sub=sub->next) {
            total += count_temp_in_operand(sub);
        }
    } else if (arg->kind == KIND_TEMP) {
        total = 1;
    }
    return total;
}
