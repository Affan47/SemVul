invalidateDynamicCost()
{


  TraceObjectMap::Iterator oit;
  for ( oit = _objectMap.begin();
        oit != _objectMap.end(); ++oit )
    (*oit).invalidate();

  TraceClassMap::Iterator cit;
  for ( cit = _classMap.begin();
        cit != _classMap.end(); ++cit )
    (*cit).invalidate();

  TraceFileMap::Iterator fit;
  for ( fit = _fileMap.begin();
        fit != _fileMap.end(); ++fit )
    (*fit).invalidate();

  TraceFunctionMap::Iterator it;
  for ( it = _functionMap.begin();
        it != _functionMap.end(); ++it ) {
    (*it).invalidateDynamicCost();
  }

  invalidate();

}
