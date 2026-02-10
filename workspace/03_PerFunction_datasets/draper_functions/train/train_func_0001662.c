compressedFunction(const QString& name,
						    TraceFile* file,
						    TraceObject* object)
{
  if ((name[0] != '(') || !name[1].isDigit())
    return _data->function(checkUnknown(name), file, object);


  int p = name.indexOf(')');
  if (p<2) {
	  error(QString("Invalid compressed function ('%1')").arg(name));
	  return 0;
  }


  int index = name.mid(1, p-1).toUInt();
  TraceFunction* f = 0;
  p++;
  while((name.length()>p) && name.at(p).isSpace()) p++;
  if (name.length()>p) {
    if (_functionVector.size() <= index) {
      int newSize = index * 2;
#if TRACE_LOADER
      qDebug() << " CachegrindLoader::functionVector enlarged to "
		<< newSize;
#endif
      _functionVector.resize(newSize);
    }

    QString realName = checkUnknown(name.mid(p));
    f = (TraceFunction*) _functionVector.at(index);
    if (f && (f->name() != realName)) {
      error(QString("Redefinition of compressed function index %1 (was '%2') to %3")
            .arg(index).arg(f->name()).arg(realName));
    }

    f = _data->function(realName, file, object);
    _functionVector.replace(index, f);

#if TRACE_LOADER
    qDebug() << "compressedFunction: Inserted at Index " << index
	      << "\n  " << f->fullName()
	      << "\n  in " << f->cls()->fullName()
	      << "\n  in " << f->file()->fullName()
	      << "\n  in " << f->object()->fullName();
#endif
  }
  else {
    if ((_functionVector.size() <= index) ||
	( (f=(TraceFunction*)_functionVector.at(index)) == 0)) {
      error(QString("Undefined compressed function index %1").arg(index));
      return 0;
    }


  }


  return f;
}
