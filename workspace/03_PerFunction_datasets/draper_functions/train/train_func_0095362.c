saveMess(t_symbol *filename, int pos)
{

  imageStruct*img=NULL;

  if(NULL==filename||NULL==filename->s_name||gensym("")==filename){
    error("no filename given!");
    return;
  }
  img=getMess(pos);

  if(img && img->data){
    mem2image(img, filename->s_name, 0);
  } else {
    error("index %d out of range (0..%d) or slot empty!", pos, m_numframes);
    return;
  }
}
