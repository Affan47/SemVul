HandlePress() {
    Event e;

    do {
	if (timer) {
	    if (!Read(0, delay * USEC_PER_DELAY_UNIT, e)) {
		AutoRepeat();
		return;
	    }
	} else {
	    Read(e);
	}
	if (e.target == this) {
	    switch (e.eventType) {
	    case EnterEvent:
		TimerOn();
		Highlight(true);
		break;
	    case LeaveEvent:
		TimerOff();
		Highlight(false);
		break;
	    case UpEvent:
		if (highlighted) {
		    AdjustView(e);
		}
		break;
	    default:
		break;
	    }
	}
    } while (e.eventType != UpEvent);
}
