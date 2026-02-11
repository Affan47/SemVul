deallocate()
{
  delete [] kxvecs;
  delete [] kyvecs;
  delete [] kzvecs;

  delete [] ug;
  memory->destroy(eg);
  memory->destroy(vg);

  delete [] sfacrl;
  delete [] sfacim;
  delete [] sfacrl_all;
  delete [] sfacim_all;
}
