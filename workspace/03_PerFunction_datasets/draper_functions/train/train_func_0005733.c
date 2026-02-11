getCopy(void) const
{
   OutPoint op;
   op.unserialize( self_.getPtr() );
   return op;
}
