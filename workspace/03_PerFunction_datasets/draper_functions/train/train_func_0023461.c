StartClicked( VDKObject*)
{
  _quizzes = 0;
  _goodAnswers = 0;

  _sbar->Push("Starting quizzes. All counters set to 0.");
  _pbar->Update(1.0);

  if(changeAnswerButtons())
    showQuizz();

  if(_book->ActivePage != QUIZZES_PAGE &&
     _book->ActivePage != SIMPLEQUIZZ_PAGE )
    _book->ActivePage = QUIZZES_PAGE;
  return true;
}
