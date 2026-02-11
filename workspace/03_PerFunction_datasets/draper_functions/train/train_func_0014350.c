moveToMainThread(QObject *obj)
{
	if (Anim::mainThread() && Anim::mainThread() != QThread::currentThread())
		obj->moveToThread(Anim::mainThread());
}
