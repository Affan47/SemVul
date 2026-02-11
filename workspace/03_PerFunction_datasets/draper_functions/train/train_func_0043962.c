Draw () {
    if (canvas != nil) {
	output->ClearRect(canvas, 0, 0, xmax, ymax);
	if (_graphic != nil) {
	    _graphic->Draw(canvas, 0, 0, xmax, ymax);
	}
    }
}
