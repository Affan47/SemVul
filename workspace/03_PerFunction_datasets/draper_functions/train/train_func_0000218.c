setCurrentOption ( const std::string value )
{
     int action = parameterOption(value);
     if (action >= 0)
          currentKeyWord_ = action;
}
