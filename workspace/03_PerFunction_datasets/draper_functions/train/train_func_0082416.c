test_hash(void)
{
  printf("\nhash\n");
  LOOP {
    size_t dim = 5;
    oct_t *oa,*ob;
    int ra,rb;
    oa = random_oct(dim,.1);
    ra = oct_hash(mo,oa);
    ob = oct_copy(mo,oa);
    rb = oct_hash(mo,ob);
    RESULT('.');
    if (ra!=rb) ERROR("different hash");
    oct_free(mo,oa); oct_free(mo,ob);
  } ENDLOOP;
}
