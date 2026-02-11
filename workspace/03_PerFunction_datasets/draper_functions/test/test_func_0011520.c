GetInterpolationStartValueAtPoint( int iPoint ) const
{
   double v = mEnv[ iPoint ]->GetVal();
   if( !mDB )
      return v;
   else
      return log10(v);
}
