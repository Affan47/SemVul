new_array(uint8_t type)
{


  if (stack > 0)
  {


    fprintf(out, "  pop r14\n");
    fprintf(out, "  mov.w &heap_ptr, r15\n");
    fprintf(out, "  mov.w r14, 0(r15)\n");


    if (type == TYPE_SHORT || type == TYPE_CHAR || type == TYPE_INT)
    {

      fprintf(out, "  rla r14\n");

      fprintf(out, "  add.w #2, r14\n");
    }
      else
    {


      fprintf(out, "  add.w #3, r14\n");
      fprintf(out, "  and.w #0xfffe, r14\n");
    }


    fprintf(out, "  add.w r14, &heap_ptr\n");


    fprintf(out, "  push r15\n");

  }
    else
  {


    fprintf(out, "  mov.w &heap_ptr, r15\n");
    fprintf(out, "  mov.w r%d, 0(r15)\n", REG_STACK(reg-1));

    if (type == TYPE_SHORT || type == TYPE_CHAR || type == TYPE_INT)
    {

      fprintf(out, "  rla r%d\n", REG_STACK(reg-1));


      fprintf(out, "  add.w #2, r%d\n", REG_STACK(reg-1));

    }
      else
    {


      fprintf(out, "  add.w #3, r%d\n", REG_STACK(reg-1));
      fprintf(out, "  and.w #0xfffe, r%d\n", REG_STACK(reg-1));
    }


    fprintf(out, "  add.w r%d, &heap_ptr\n", REG_STACK(reg-1));


    fprintf(out, "  add.w #2, r15\n");
    fprintf(out, "  mov.w r15, r%d\n", REG_STACK(reg-1));
  }

  return 0;
}
