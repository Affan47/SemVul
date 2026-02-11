setCompletionObject(KCompletion* compObj, bool hsig)
{
    if ( compObj ) {


        compObj->setOrder( KCompletion::Sorted );
    }
    KComboBox::setCompletionObject( compObj, hsig );
}
