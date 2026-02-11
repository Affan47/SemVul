setSlice(int v)
{
    ((Fl_Valuator*)sliceSlider)->value(v);
    sliceValue->value(v);

    if (displayslice)
	displayslice(v);
}
