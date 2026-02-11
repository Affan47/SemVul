applyRowCut( const OsiRowCut & rc)
{
   double lb, ub;
   CoinPackedVector rowVec;

   freeCachedData(KEEPCACHED_COLUMN);

   rowVec = rc.row();
   lb = rc.lb();
   ub = rc.ub();

   addRow(rowVec, lb, ub);
}
