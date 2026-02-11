th_comment_query_count(th_comment *_tc,char *_tag){
  long i;
  int  tag_len;
  int  count;
  tag_len=strlen(_tag);
  count=0;
  for(i=0;i<_tc->comments;i++){
    if(!oc_tagcompare(_tc->user_comments[i],_tag,tag_len))count++;
  }
  return count;
}
