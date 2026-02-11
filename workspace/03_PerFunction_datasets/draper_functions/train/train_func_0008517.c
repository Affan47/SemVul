editWidget() const
{
    PreventDuplicatesEditWidget* e = new PreventDuplicatesEditWidget( m_field );
    connect( e, SIGNAL(fieldChanged(int)), this, SLOT(setField(int)) );
    return e;
}
