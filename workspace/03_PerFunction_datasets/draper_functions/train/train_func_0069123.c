setCurveCmb(DigitDoc* doc)
{

  ASSERT_ENGAUGE(curveCmb != 0);
  curveCmb->attachToDocument(doc);

  if (doc)
  {

    curveCmb->setCurrentText(doc->curveCmbText());
  }
}
