init() {
    deck_ = new Deck;
    for (TelltaleFlags i = 0; i < TelltaleState::max_flags; i++) {
	index_[i] = -1;
    }
    state()->set(TelltaleState::is_enabled, true);
    body(new Target(deck_, TargetPrimitiveHit));
}
