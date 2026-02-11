pickUp() {
	try {

		Effect *effect = new Effect(EFFECT_MUSHROOM_CATCH, mName + "Effect", mSceneMgr, "", getRealPosition());
		effect->createParticles("MushroomPickup" + StringConverter::toString(mColor+1));
		effect->setCurrentSpeed(mCurrentSpeed);


		effect = new Effect(EFFECT_MUSHROOM_CATCH, mName + "EffectSparks", mSceneMgr, "", getRealPosition());
		effect->createParticles("MushroomSparks" + StringConverter::toString(mColor+1));
		effect->setDuration(1.0f);
		effect->setCurrentSpeed(mCurrentSpeed);

		ColourValue col;
		switch(mColor) {
			default:
			case MUSHROOM_RED: col = ColourValue(1,0,0); break;
			case MUSHROOM_GREEN: col = ColourValue(0,1,0); break;
			case MUSHROOM_BLUE: col = ColourValue(0,0,1); break;
		}
		effect->createLight(col);
	}
	catch(...) {

	}

}
