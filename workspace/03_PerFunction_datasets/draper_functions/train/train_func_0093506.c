is_mapped(const bam1_core_t *core)
{

  if (core->flag&BAM_FUNMAP)
    return false;

  return true;
}
