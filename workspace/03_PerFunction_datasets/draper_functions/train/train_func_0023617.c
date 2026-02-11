ChairCell( vtkIdType c, const CellType & cell )
    {
    CellType tmpCell = RotateCell(cell, c);
    CellType::iterator it = tmpCell.end();
    tmpCell.erase(--it);
    CellType outputCell = tmpCell;
    for (CellType::reverse_iterator cit = tmpCell.rbegin(); cit != tmpCell.rend(); ++cit)
      outputCell.push_back(*cit + 8);
    return outputCell;
    }
