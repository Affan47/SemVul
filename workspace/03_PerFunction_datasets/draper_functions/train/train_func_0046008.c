GetCellDataRange(int cellComp, int index,
     float *min, float *max)
{
  if (index >= this->VectorLength->GetValue(cellComp) || index < 0)
    {
    index = 0;
    }
  *min = this->Minimum->GetValue(cellComp);
  *max = this->Maximum->GetValue(cellComp);
}
