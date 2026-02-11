intervalSelected()
{

    if (main->currentRideItem() == ride) {


        table->selectionModel()->select(QItemSelection(model->index(0,0),
                                                       model->index(ride->ride()->dataPoints().count(),model->columnCount()-1)),
                                                       QItemSelectionModel::Clear);


        foreach(QTreeWidgetItem *x, main->allIntervalItems()->treeWidget()->selectedItems()) {

            IntervalItem *current = (IntervalItem*)x;

            if (current != NULL && current->isSelected() == true) {


                int start = ride->ride()->timeIndex(current->start);
                int end = ride->ride()->timeIndex(current->stop);


                table->selectionModel()->clearSelection();
                table->selectionModel()->setCurrentIndex(model->index(start,0), QItemSelectionModel::Select);
                table->selectionModel()->select(QItemSelection(model->index(start,0),
                                                                   model->index(end,model->columnCount()-1)),
                                                                    QItemSelectionModel::Select);
            }
        }
    }
}
