additionalAction( Annotation::AdditionalActionType type ) const
{
    if ( pdfAnnot->getType() != Annot::typeScreen && pdfAnnot->getType() != Annot::typeWidget )
        return 0;

    Annot::AdditionalActionsType actionType = Annot::actionCursorEntering;
    switch ( type )
    {
        case Annotation::CursorEnteringAction: actionType = Annot::actionCursorEntering; break;
        case Annotation::CursorLeavingAction: actionType = Annot::actionCursorLeaving; break;
        case Annotation::MousePressedAction: actionType = Annot::actionMousePressed; break;
        case Annotation::MouseReleasedAction: actionType = Annot::actionMouseReleased; break;
        case Annotation::FocusInAction: actionType = Annot::actionFocusIn; break;
        case Annotation::FocusOutAction: actionType = Annot::actionFocusOut; break;
        case Annotation::PageOpeningAction: actionType = Annot::actionPageOpening; break;
        case Annotation::PageClosingAction: actionType = Annot::actionPageClosing; break;
        case Annotation::PageVisibleAction: actionType = Annot::actionPageVisible; break;
        case Annotation::PageInvisibleAction: actionType = Annot::actionPageInvisible; break;
    }

    ::LinkAction *linkAction = 0;
    if ( pdfAnnot->getType() == Annot::typeScreen )
        linkAction = static_cast<AnnotScreen*>( pdfAnnot )->getAdditionalAction( actionType );
    else
        linkAction = static_cast<AnnotWidget*>( pdfAnnot )->getAdditionalAction( actionType );

    Link *link = 0;

    if ( linkAction )
        link = PageData::convertLinkActionToLink( linkAction, parentDoc, QRectF() );

    return link;
}
