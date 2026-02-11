deactivate(TimeHandler* th)
{
    std::list<TimeHandler*>::iterator i;

    i = find(self.handlers.begin(), self.handlers.end(), th);
    if (i != self.handlers.end()) {
        *i = 0;
    }
}
