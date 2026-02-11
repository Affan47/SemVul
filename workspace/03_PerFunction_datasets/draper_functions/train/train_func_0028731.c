isDuplicate(unsigned row_)
{ return (MSView::model()!=0&&row_!=0)?vector()(row_)==vector()(row_-1)?MSTrue:MSFalse:MSFalse;}
