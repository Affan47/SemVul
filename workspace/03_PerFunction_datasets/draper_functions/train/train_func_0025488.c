calcDevRegularGrid()
    {
      const TensorGrid &regularTensorGrid = getTensorRegularGrid();
      m_regDevStressGrid = DoubleGrid(m_bBox, m_gridSpacing);

      TensorGrid::CellConstIterator cellIt = regularTensorGrid.getCellIterator();
      while (cellIt.hasNext())
      {
        TensorGrid::Cell::ConstIterator pairIt = cellIt.next().getIterator();
        while (pairIt.hasNext())
        {
          const Tensor &tensor = pairIt.next().getValue();
          m_regDevStressGrid.insert(
            tensor.getPos(),
            getRealDevStress(tensor)
          );
        }
      }
    }
