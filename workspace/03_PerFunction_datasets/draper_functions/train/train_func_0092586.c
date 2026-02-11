add_body_abstotal(b_id,v)
body_id b_id; REAL v;
{ struct body *b;
  if ( !valid_id(b_id) ) return;
  b = bptr(b_id);
  b->abstotal += fabs(v);
}
