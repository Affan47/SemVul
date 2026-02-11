setStyle(RenderStyle *_style)
{
    ETableLayout oldTableLayout = style() ? style()->tableLayout() : TAUTO;
    if ( _style->display() == INLINE ) _style->setDisplay( INLINE_TABLE );
    if ( _style->display() != INLINE_TABLE ) _style->setDisplay(TABLE);
    if ( !_style->flowAroundFloats() ) _style->setFlowAroundFloats(true);
    RenderBlock::setStyle(_style);


    setInline(style()->display()==INLINE_TABLE && !isPositioned());
    setReplaced(style()->display()==INLINE_TABLE);


    hspacing = collapseBorders() ? 0 : style()->borderHorizontalSpacing();
    vspacing = collapseBorders() ? 0 : style()->borderVerticalSpacing();
    columnPos[0] = hspacing;

    if ( !tableLayout || style()->tableLayout() != oldTableLayout ) {
	delete tableLayout;


	if (style()->tableLayout() == TFIXED && !style()->width().isAuto()) {
	    tableLayout = new FixedTableLayout(this);
#ifdef DEBUG_LAYOUT
	    kDebug( 6040 ) << "using fixed table layout";
#endif
	} else
	    tableLayout = new AutoTableLayout(this);
    }
}
