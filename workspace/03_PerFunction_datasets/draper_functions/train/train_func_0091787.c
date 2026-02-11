Dequeue() {
  if(IsEmpty()) return false;
  end=end->prev;
  delete end->next;
  end->next=NULL;
  return true;
}
