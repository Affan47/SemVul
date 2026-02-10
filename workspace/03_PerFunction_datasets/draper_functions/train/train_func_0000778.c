Init(const char* name, Interactor* i) {
    if (name != nil) {
	SetInstance(name);
    }
    enabled_ = true;
    parent_ = nil;
    state_ = new ControlState;
    state_->Attach(this);
    input = new Sensor;
    input->Catch(EnterEvent);
    input->Catch(LeaveEvent);
    input->Catch(DownEvent);
    input->Catch(UpEvent);
    if (i != nil) {
	Insert(i);
    }
}
