New_Vector( int subNode )
{
   Node *this, *that;
   int n;

   n = Alloc_Node();
   if( n >= 0 ) {
      this              = gParse.Nodes + n;
      that              = gParse.Nodes + subNode;
      this->type        = that->type;
      this->nSubNodes   = 1;
      this->SubNodes[0] = subNode;
      this->operation   = '{';
      this->DoOp        = Do_Vector;
   }

   return( n );
}
