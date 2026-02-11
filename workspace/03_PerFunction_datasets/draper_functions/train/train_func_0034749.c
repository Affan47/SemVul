Evaluate_Parser( long firstRow, long nRows )


{
   int     i, column;
   long    offset, rowOffset;

   gParse.firstRow = firstRow;
   gParse.nRows    = nRows;


   rowOffset = firstRow - gParse.firstDataRow;
   for( i=0; i<gParse.nNodes; i++ ) {
     if(    OPER(i) >  0 || OPER(i) == CONST_OP ) continue;

      column = -OPER(i);
      offset = gParse.varData[column].nelem * rowOffset;

      gParse.Nodes[i].value.undef = gParse.varData[column].undef + offset;

      switch( gParse.Nodes[i].type ) {
      case BITSTR:
	 gParse.Nodes[i].value.data.strptr =
	    (char**)gParse.varData[column].data + rowOffset;
	 gParse.Nodes[i].value.undef       = NULL;
	 break;
      case STRING:
	 gParse.Nodes[i].value.data.strptr =
	    (char**)gParse.varData[column].data + rowOffset;
	 gParse.Nodes[i].value.undef = gParse.varData[column].undef + rowOffset;
	 break;
      case BOOLEAN:
	 gParse.Nodes[i].value.data.logptr =
	    (char*)gParse.varData[column].data + offset;
	 break;
      case LONG:
	 gParse.Nodes[i].value.data.lngptr =
	    (long*)gParse.varData[column].data + offset;
	 break;
      case DOUBLE:
	 gParse.Nodes[i].value.data.dblptr =
	    (double*)gParse.varData[column].data + offset;
	 break;
      }
   }

   Evaluate_Node( gParse.resultNode );
}
