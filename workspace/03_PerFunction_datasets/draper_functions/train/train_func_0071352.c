GetEllipse2() {
    Picture* pic = (Picture*)GetGraphic();
    Iterator i;
    pic->First(i);
    pic->Next(i);
    if (pic->Done(i))
	return nil;
    else
        return (SF_Ellipse*)pic->GetGraphic(i);
}
