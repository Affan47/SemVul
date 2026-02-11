passInEventHandler(const ClpEventHandler * eventHandler)
{
     delete eventHandler_;
     eventHandler_ = eventHandler->clone();
     eventHandler_->setSimplex(this);
}
