Initialise()
{
  testImageType();

  if( !isFile ){

    measureHorizontalAngles();


    measureVerticalAngles();
  }

  else{
    horizontalAnglesList.push_front( 0 );
    verticalAnglesList.push_front( 90 );
  }

}
