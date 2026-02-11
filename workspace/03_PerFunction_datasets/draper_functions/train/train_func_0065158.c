MoveBall(Ball* ball)
{
   switch (ball->GetDirection()) {
   case Ball::MovingLeft:
      ball->SetDirection(Ball::MovingDown);
      _start->PutBall(ball);
      break;
   case Ball::MovingUp:
      ball->SetDirection(Ball::MovingRight);
      _end->PutBall(ball);
      break;
   case Ball::MovingRight:
      ball->SetDirection(Ball::MovingUp);
      _end->PutBall(ball);
      break;
   case Ball::MovingDown:
      ball->SetDirection(Ball::MovingLeft);
      _start->PutBall(ball);
      break;
   default:
      break;
   }
}
