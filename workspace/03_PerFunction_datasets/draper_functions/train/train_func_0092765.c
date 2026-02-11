EvaluateEdge( const double* p0, double* midpt, const double* p1, int field_start )
{
  static double weights[27];
  static int dummySubId=-1;
  double realMidPt[ 3 ];

  this->CurrentCellData->EvaluateLocation( dummySubId, midpt + 3, realMidPt, weights );
  double chord2 = 0.;
  double tmp;
  int c;
  for ( c = 0; c < 3; ++c )
    {
    tmp = midpt[c] - realMidPt[c];
    chord2 += tmp * tmp;
    }

  bool rval = chord2 > this->ChordError2;
  if ( rval )
    {
    for ( c = 0; c < 3; ++c )
      midpt[c] = realMidPt[c];

    this->EvaluateFields( midpt, weights, field_start );
    return true;
    }

  int active = this->GetActiveFieldCriteria();
  if ( active )
    {
    double real_pf[6+vtkStreamingTessellator::MaxFieldSize];
    std::copy( midpt, midpt + field_start, real_pf );
    this->EvaluateFields( real_pf, weights, field_start );

    rval = this->FixedFieldErrorEval( p0, midpt, real_pf, p1, field_start, active, this->FieldError2 );
#if 0
    cout << (rval ? "*" : " ")
      <<    "p0 " <<      p0[13] << ", " <<      p0[14] << ", " <<      p0[15]
      << "   md " <<   midpt[13] << ", " <<   midpt[14] << ", " <<   midpt[15]
      << "   cm " << real_pf[13] << ", " << real_pf[14] << ", " << real_pf[15]
      << "   p1 " <<      p1[13] << ", " <<      p1[14] << ", " <<      p1[15] << endl;
#endif
    if ( rval )
      {
      std::copy( real_pf+field_start, real_pf+field_start+this->FieldOffsets[this->NumberOfFields], midpt+field_start );
      }
    }

  return rval;
}
