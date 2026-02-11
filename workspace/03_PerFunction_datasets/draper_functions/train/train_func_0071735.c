return_void(int local_count)
{
  fprintf(out, "  ;; return_void(%d)\n", local_count);
  restore_stack(local_count);
  while (stack > 0) { fprintf(out, "  pop bc\n"); stack--; }
  if (!is_main) { fprintf(out, "  pop iy\n"); }
  fprintf(out, "  ret\n");
  return 0;
}
