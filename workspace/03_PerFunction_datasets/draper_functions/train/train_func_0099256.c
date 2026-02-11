setCurrentOption ( int value , bool printIt)
{
     if (printIt && value != currentKeyWord_)
          std::cout << "Option for " << name_ << " changed from "
                    << definedKeyWords_[currentKeyWord_] << " to "
                    << definedKeyWords_[value] << std::endl;

     currentKeyWord_ = value;
}
