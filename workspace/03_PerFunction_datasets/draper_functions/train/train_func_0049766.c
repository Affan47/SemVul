new_rel_from_abs (bfd_vma value)
{
  asection *s = expld.section;

  if (s == bfd_abs_section_ptr && expld.phase == lang_final_phase_enum)
    s = section_for_dot ();
  expld.result.valid_p = TRUE;
  expld.result.value = value - s->vma;
  expld.result.str = NULL;
  expld.result.section = s;
}
