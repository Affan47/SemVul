GraalAddUndoRec( Rectangle )

   rdsrec_list *Rectangle;
{
  graalundorec *UndoRec;

  rdsbegin();

  UndoRec             = GraalAllocUndoRec();
  UndoRec->RECTANGLE  = Rectangle;
  UndoRec->NEXT       = GraalHeadUndo->UNDO;
  GraalHeadUndo->UNDO = UndoRec;

  rdsend();
}
