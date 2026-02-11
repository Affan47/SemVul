ClearStyles() {

	for (unsigned int i=0; i<stylesSize; i++) {
		if (i != STYLE_DEFAULT) {
			styles[i].ClearTo(styles[STYLE_DEFAULT]);
		}
	}
	styles[STYLE_LINENUMBER].back = Platform::Chrome();


	styles[STYLE_CALLTIP].back = ColourDesired(0xff, 0xff, 0xff);
	styles[STYLE_CALLTIP].fore = ColourDesired(0x80, 0x80, 0x80);
}
