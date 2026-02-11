increaseEmittedEmitterPool(size_t size)
    {

        if (mEmittedEmitterPool.empty())
            return;

        EmittedEmitterPool::iterator emittedEmitterPoolIterator;
        ParticleEmitterList::iterator emitterIterator;
        ParticleEmitter* clonedEmitter = 0;
        String name = BLANKSTRING;
        EmittedEmitterList* e = 0;
        size_t maxNumberOfEmitters = size / mEmittedEmitterPool.size();
        size_t oldSize = 0;


        for (emittedEmitterPoolIterator = mEmittedEmitterPool.begin(); emittedEmitterPoolIterator != mEmittedEmitterPool.end(); ++emittedEmitterPoolIterator)
        {
            name = emittedEmitterPoolIterator->first;
            e = &emittedEmitterPoolIterator->second;


            for (emitterIterator = mEmitters.begin(); emitterIterator != mEmitters.end(); ++emitterIterator)
            {
                ParticleEmitter* emitter = *emitterIterator;
                if (emitter &&
                    name != BLANKSTRING &&
                    name == emitter->getName())
                {

                    oldSize = e->size();
                    for (size_t t = oldSize; t < maxNumberOfEmitters; ++t)
                    {
                        clonedEmitter = ParticleSystemManager::getSingleton()._createEmitter(emitter->getType(), this);
                        emitter->copyParametersTo(clonedEmitter);
                        clonedEmitter->setEmitted(emitter->isEmitted());


                        if (clonedEmitter->getDuration() > 0.0f &&
                            (clonedEmitter->getRepeatDelay() > 0.0f || clonedEmitter->getMinRepeatDelay() > 0.0f))
                            clonedEmitter->setEnabled(false);


                        e->push_back(clonedEmitter);
                    }
                }
            }
        }
    }
