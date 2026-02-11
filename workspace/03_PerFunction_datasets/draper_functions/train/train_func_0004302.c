operator*=(Real r)
{
   REPORT
   Tracer tr("SubMatrix(*= or /= Real)");

   Try
   {
      SetUpLHS();
      MatrixRow mr(gm, LoadOnEntry+StoreOnExit+Node_pairPart, row_skip);

      MatrixRowCol sub; int i = row_number;
      while (i--)
      {
         mr.SubRowCol(sub, col_skip, col_number);
         sub.Multiply(r); mr.Next();
      }
   }

   CatchAll
   {
      ReThrow;
   }
}
