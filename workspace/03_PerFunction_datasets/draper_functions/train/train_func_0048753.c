MK_Trans(struct mathkern *mk,real transform[6]) {
    if ( mk==NULL )
return;
    MKV_Trans(&mk->top_right,transform);
    MKV_Trans(&mk->top_left ,transform);
    MKV_Trans(&mk->bottom_right,transform);
    MKV_Trans(&mk->bottom_left ,transform);
}
